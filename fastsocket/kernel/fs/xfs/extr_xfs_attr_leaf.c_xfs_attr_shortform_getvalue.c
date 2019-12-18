#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {size_t namelen; int flags; scalar_t__ valuelen; int /*<<< orphan*/  value; int /*<<< orphan*/  name; TYPE_4__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;
struct TYPE_16__ {int count; } ;
struct TYPE_18__ {TYPE_5__ hdr; TYPE_8__* list; } ;
typedef  TYPE_7__ xfs_attr_shortform_t ;
struct TYPE_19__ {size_t namelen; scalar_t__ valuelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  flags; } ;
typedef  TYPE_8__ xfs_attr_sf_entry_t ;
struct TYPE_12__ {scalar_t__ di_aformat; } ;
struct TYPE_15__ {TYPE_3__* i_afp; TYPE_1__ i_d; } ;
struct TYPE_13__ {scalar_t__ if_data; } ;
struct TYPE_14__ {TYPE_2__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOATTR ; 
 int /*<<< orphan*/  ERANGE ; 
 TYPE_8__* XFS_ATTR_SF_NEXTENTRY (TYPE_8__*) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_IFINLINE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int,int /*<<< orphan*/ ) ; 

int
xfs_attr_shortform_getvalue(xfs_da_args_t *args)
{
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	int i;

	ASSERT(args->dp->i_d.di_aformat == XFS_IFINLINE);
	sf = (xfs_attr_shortform_t *)args->dp->i_afp->if_u1.if_data;
	sfe = &sf->list[0];
	for (i = 0; i < sf->hdr.count;
				sfe = XFS_ATTR_SF_NEXTENTRY(sfe), i++) {
		if (sfe->namelen != args->namelen)
			continue;
		if (memcmp(args->name, sfe->nameval, args->namelen) != 0)
			continue;
		if (!xfs_attr_namesp_match(args->flags, sfe->flags))
			continue;
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = sfe->valuelen;
			return(XFS_ERROR(EEXIST));
		}
		if (args->valuelen < sfe->valuelen) {
			args->valuelen = sfe->valuelen;
			return(XFS_ERROR(ERANGE));
		}
		args->valuelen = sfe->valuelen;
		memcpy(args->value, &sfe->nameval[args->namelen],
						    args->valuelen);
		return(XFS_ERROR(EEXIST));
	}
	return(XFS_ERROR(ENOATTR));
}