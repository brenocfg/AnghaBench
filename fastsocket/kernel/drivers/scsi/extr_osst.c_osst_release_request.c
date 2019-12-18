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
struct osst_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct osst_request*) ; 

__attribute__((used)) static void osst_release_request(struct osst_request *streq)
{
	kfree(streq);
}