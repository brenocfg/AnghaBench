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

/* Variables and functions */
 int /*<<< orphan*/  cprop_absaltered ; 
 int /*<<< orphan*/  cprop_avin ; 
 int /*<<< orphan*/  cprop_avout ; 
 int /*<<< orphan*/  cprop_pavloc ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_cprop_mem (void)
{
  sbitmap_vector_free (cprop_pavloc);
  sbitmap_vector_free (cprop_absaltered);
  sbitmap_vector_free (cprop_avin);
  sbitmap_vector_free (cprop_avout);
}