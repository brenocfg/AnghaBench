#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gfs2_inode {int dummy; } ;
struct gfs2_ea_location {int /*<<< orphan*/  el_ea; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  GFS2_EA2DATA (int /*<<< orphan*/ ) ; 
 size_t GFS2_EA_DATA_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ GFS2_EA_IS_STUFFED (int /*<<< orphan*/ ) ; 
 int ea_get_unstuffed (struct gfs2_inode*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int gfs2_ea_get_copy(struct gfs2_inode *ip, struct gfs2_ea_location *el,
			    char *data, size_t size)
{
	int ret;
	size_t len = GFS2_EA_DATA_LEN(el->el_ea);
	if (len > size)
		return -ERANGE;

	if (GFS2_EA_IS_STUFFED(el->el_ea)) {
		memcpy(data, GFS2_EA2DATA(el->el_ea), len);
		return len;
	}
	ret = ea_get_unstuffed(ip, el->el_ea, data);
	if (ret < 0)
		return ret;
	return len;
}