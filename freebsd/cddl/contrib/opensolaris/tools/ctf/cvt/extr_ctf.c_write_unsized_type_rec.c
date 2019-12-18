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
typedef  int /*<<< orphan*/  ctf_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  ctt_size; int /*<<< orphan*/  ctt_info; int /*<<< orphan*/  ctt_name; } ;
typedef  TYPE_1__ ctf_stype_t ;
typedef  int /*<<< orphan*/  ctf_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_buf_write (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ target_requires_swap ; 

__attribute__((used)) static void
write_unsized_type_rec(ctf_buf_t *b, ctf_type_t *ctt)
{
	ctf_stype_t *cts = (ctf_stype_t *)ctt;

	if (target_requires_swap) {
		SWAP_32(cts->ctt_name);
		SWAP_16(cts->ctt_info);
		SWAP_16(cts->ctt_size);
	}

	ctf_buf_write(b, cts, sizeof (*cts));
}