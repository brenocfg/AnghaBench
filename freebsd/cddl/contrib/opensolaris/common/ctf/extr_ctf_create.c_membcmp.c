#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong_t ;
struct TYPE_4__ {scalar_t__ ctm_offset; } ;
typedef  TYPE_1__ ctf_membinfo_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctb_type; int /*<<< orphan*/  ctb_file; } ;
typedef  TYPE_2__ ctf_bundle_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 scalar_t__ ctf_member_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 

__attribute__((used)) static int
membcmp(const char *name, ctf_id_t type, ulong_t offset, void *arg)
{
	ctf_bundle_t *ctb = arg;
	ctf_membinfo_t ctm;

	return (ctf_member_info(ctb->ctb_file, ctb->ctb_type,
	    name, &ctm) == CTF_ERR || ctm.ctm_offset != offset);
}