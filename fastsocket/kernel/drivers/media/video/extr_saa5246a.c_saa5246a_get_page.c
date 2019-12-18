#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pgbuf; int start; int end; scalar_t__ buffer; } ;
typedef  TYPE_1__ vtx_pagereq_t ;
struct saa5246a_device {scalar_t__* is_searching; } ;

/* Variables and functions */
 int COLUMN (int) ; 
 int /*<<< orphan*/  COMMAND_END ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_DAUS ; 
 int POS_HEADER_END ; 
 int /*<<< orphan*/  POS_HEADER_START ; 
 int POS_TIME_END ; 
 int /*<<< orphan*/  POS_TIME_START ; 
 int R8_ACTIVE_CHAPTER_4 ; 
 int R8_DO_NOT_CLEAR_MEMORY ; 
 int /*<<< orphan*/  R9_CURSER_ROW_0 ; 
 scalar_t__ REQ_CONTAINS_HEADER (TYPE_1__*) ; 
 scalar_t__ REQ_CONTAINS_TIME (TYPE_1__*) ; 
 int /*<<< orphan*/  ROW (int) ; 
 int /*<<< orphan*/  SAA5246A_REGISTER_R8 ; 
 int VTX_PAGESIZE ; 
 scalar_t__ copy_to_user (scalar_t__,char*,int) ; 
 scalar_t__ i2c_getdata (struct saa5246a_device*,int,char*) ; 
 scalar_t__ i2c_senddata (struct saa5246a_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static inline int saa5246a_get_page(struct saa5246a_device *t,
	vtx_pagereq_t *req)
{
	int start, end, size;
	char *buf;
	int err;

	if (req->pgbuf < 0 || req->pgbuf >= NUM_DAUS ||
	    req->start < 0 || req->start > req->end || req->end >= VTX_PAGESIZE)
		return -EINVAL;

	buf = kmalloc(VTX_PAGESIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* Read "normal" part of page */
	err = -EIO;

	end = min(req->end, VTX_PAGESIZE - 1);
	if (i2c_senddata(t, SAA5246A_REGISTER_R8,
			req->pgbuf | R8_DO_NOT_CLEAR_MEMORY,
			ROW(req->start), COLUMN(req->start), COMMAND_END))
		goto out;
	if (i2c_getdata(t, end - req->start + 1, buf))
		goto out;
	err = -EFAULT;
	if (copy_to_user(req->buffer, buf, end - req->start + 1))
		goto out;

	/* Always get the time from buffer 4, since this stupid SAA5246A only
	 * updates the currently displayed buffer...
	 */
	if (REQ_CONTAINS_TIME(req)) {
		start = max(req->start, POS_TIME_START);
		end   = min(req->end,   POS_TIME_END);
		size = end - start + 1;
		err = -EINVAL;
		if (size < 0)
			goto out;
		err = -EIO;
		if (i2c_senddata(t, SAA5246A_REGISTER_R8,
				R8_ACTIVE_CHAPTER_4 | R8_DO_NOT_CLEAR_MEMORY,
				R9_CURSER_ROW_0, start, COMMAND_END))
			goto out;
		if (i2c_getdata(t, size, buf))
			goto out;
		err = -EFAULT;
		if (copy_to_user(req->buffer + start - req->start, buf, size))
			goto out;
	}
	/* Insert the header from buffer 4 only, if acquisition circuit is still searching for a page */
	if (REQ_CONTAINS_HEADER(req) && t->is_searching[req->pgbuf]) {
		start = max(req->start, POS_HEADER_START);
		end   = min(req->end,   POS_HEADER_END);
		size = end - start + 1;
		err = -EINVAL;
		if (size < 0)
			goto out;
		err = -EIO;
		if (i2c_senddata(t, SAA5246A_REGISTER_R8,
				R8_ACTIVE_CHAPTER_4 | R8_DO_NOT_CLEAR_MEMORY,
				R9_CURSER_ROW_0, start, COMMAND_END))
			goto out;
		if (i2c_getdata(t, end - start + 1, buf))
			goto out;
		err = -EFAULT;
		if (copy_to_user(req->buffer + start - req->start, buf, size))
			goto out;
	}
	err = 0;
out:
	kfree(buf);
	return err;
}