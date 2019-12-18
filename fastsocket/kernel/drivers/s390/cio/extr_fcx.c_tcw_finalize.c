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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  tcat ;
struct tidaw {int /*<<< orphan*/  flags; } ;
struct tcw {int flags; int tccbl; void* output_count; scalar_t__ w; void* input_count; scalar_t__ r; } ;
struct tccb_tcat {scalar_t__ count; } ;
struct tccb {int /*<<< orphan*/ * tca; } ;

/* Variables and functions */
 scalar_t__ ALIGN (void*,int) ; 
 int TCW_FLAGS_OUTPUT_TIDA ; 
 int /*<<< orphan*/  TIDAW_FLAGS_LAST ; 
 scalar_t__ calc_cbc_size (struct tidaw*,int) ; 
 void* calc_dcw_count (struct tccb*) ; 
 int /*<<< orphan*/  memset (struct tccb_tcat*,int /*<<< orphan*/ ,int) ; 
 int tca_size (struct tccb*) ; 
 struct tidaw* tcw_get_data (struct tcw*) ; 
 struct tccb* tcw_get_tccb (struct tcw*) ; 

void tcw_finalize(struct tcw *tcw, int num_tidaws)
{
	struct tidaw *tidaw;
	struct tccb *tccb;
	struct tccb_tcat *tcat;
	u32 count;

	/* Terminate tidaw list. */
	tidaw = tcw_get_data(tcw);
	if (num_tidaws > 0)
		tidaw[num_tidaws - 1].flags |= TIDAW_FLAGS_LAST;
	/* Add tcat to tccb. */
	tccb = tcw_get_tccb(tcw);
	tcat = (struct tccb_tcat *) &tccb->tca[tca_size(tccb)];
	memset(tcat, 0, sizeof(tcat));
	/* Calculate tcw input/output count and tcat transport count. */
	count = calc_dcw_count(tccb);
	if (tcw->w && (tcw->flags & TCW_FLAGS_OUTPUT_TIDA))
		count += calc_cbc_size(tidaw, num_tidaws);
	if (tcw->r)
		tcw->input_count = count;
	else if (tcw->w)
		tcw->output_count = count;
	tcat->count = ALIGN(count, 4) + 4;
	/* Calculate tccbl. */
	tcw->tccbl = (sizeof(struct tccb) + tca_size(tccb) +
		      sizeof(struct tccb_tcat) - 20) >> 2;
}