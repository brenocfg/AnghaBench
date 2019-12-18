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
struct ata_queued_cmd {int /*<<< orphan*/  result_tf; int /*<<< orphan*/  tag; int /*<<< orphan*/  ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  sil24_read_tf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sil24_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	sil24_read_tf(qc->ap, qc->tag, &qc->result_tf);
	return true;
}