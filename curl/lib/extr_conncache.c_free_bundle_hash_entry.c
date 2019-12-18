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
struct connectbundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bundle_destroy (struct connectbundle*) ; 

__attribute__((used)) static void free_bundle_hash_entry(void *freethis)
{
  struct connectbundle *b = (struct connectbundle *) freethis;

  bundle_destroy(b);
}