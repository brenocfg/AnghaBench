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
struct sctp_ssnmap {int malloced; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int MAX_KMALLOC_SIZE ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct sctp_ssnmap*) ; 
 struct sctp_ssnmap* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ssnmap_init (struct sctp_ssnmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sctp_ssnmap_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssnmap ; 

struct sctp_ssnmap *sctp_ssnmap_new(__u16 in, __u16 out,
				    gfp_t gfp)
{
	struct sctp_ssnmap *retval;
	int size;

	size = sctp_ssnmap_size(in, out);
	if (size <= MAX_KMALLOC_SIZE)
		retval = kmalloc(size, gfp);
	else
		retval = (struct sctp_ssnmap *)
			  __get_free_pages(gfp, get_order(size));
	if (!retval)
		goto fail;

	if (!sctp_ssnmap_init(retval, in, out))
		goto fail_map;

	retval->malloced = 1;
	SCTP_DBG_OBJCNT_INC(ssnmap);

	return retval;

fail_map:
	if (size <= MAX_KMALLOC_SIZE)
		kfree(retval);
	else
		free_pages((unsigned long)retval, get_order(size));
fail:
	return NULL;
}