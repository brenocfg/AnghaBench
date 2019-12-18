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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {scalar_t__ dtbd_oldest; int dtbd_size; char* dtbd_data; } ;
typedef  TYPE_1__ dtrace_bufdesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 char* dt_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_free (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
dt_unring_buf(dtrace_hdl_t *dtp, dtrace_bufdesc_t *buf)
{
	int misalign;
	char *newdata, *ndp;

	if (buf->dtbd_oldest == 0)
		return (0);

	misalign = buf->dtbd_oldest & (sizeof (uint64_t) - 1);
	newdata = ndp = dt_alloc(dtp, buf->dtbd_size + misalign);

	if (newdata == NULL)
		return (-1);

	assert(0 == (buf->dtbd_size & (sizeof (uint64_t) - 1)));

	bzero(ndp, misalign);
	ndp += misalign;

	bcopy(buf->dtbd_data + buf->dtbd_oldest, ndp,
	    buf->dtbd_size - buf->dtbd_oldest);
	ndp += buf->dtbd_size - buf->dtbd_oldest;

	bcopy(buf->dtbd_data, ndp, buf->dtbd_oldest);

	dt_free(dtp, buf->dtbd_data);
	buf->dtbd_oldest = 0;
	buf->dtbd_data = newdata;
	buf->dtbd_size += misalign;

	return (0);
}