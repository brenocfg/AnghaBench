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
struct chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct chunk) ; 

__attribute__((used)) static void
chunk_end(struct chunk **chunk_var)
{
   struct chunk *chunk = *chunk_var;

   *chunk_var = NULL;
   CLEAR(*chunk);
}