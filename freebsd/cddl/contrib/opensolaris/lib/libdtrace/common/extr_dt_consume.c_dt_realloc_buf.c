#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {int dtbd_size; int dtbd_oldest; char* dtbd_data; } ;
typedef  TYPE_1__ dtrace_bufdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 char* dt_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
dt_realloc_buf(dtrace_hdl_t *dtp, dtrace_bufdesc_t *buf, int cursize)
{
	uint64_t used = buf->dtbd_size - buf->dtbd_oldest;
	if (used < cursize / 2) {
		int misalign = buf->dtbd_oldest & (sizeof (uint64_t) - 1);
		char *newdata = dt_alloc(dtp, used + misalign);
		if (newdata == NULL)
			return;
		bzero(newdata, misalign);
		bcopy(buf->dtbd_data + buf->dtbd_oldest,
		    newdata + misalign, used);
		dt_free(dtp, buf->dtbd_data);
		buf->dtbd_oldest = misalign;
		buf->dtbd_size = used + misalign;
		buf->dtbd_data = newdata;
	}
}