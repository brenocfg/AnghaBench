#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ctb_type; int /*<<< orphan*/  ctb_file; } ;
typedef  TYPE_1__ ctf_bundle_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 scalar_t__ ctf_add_enumerator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
enumadd(const char *name, int value, void *arg)
{
	ctf_bundle_t *ctb = arg;

	return (ctf_add_enumerator(ctb->ctb_file, ctb->ctb_type,
	    name, value) == CTF_ERR);
}