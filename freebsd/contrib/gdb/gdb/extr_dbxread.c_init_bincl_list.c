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
struct objfile {int /*<<< orphan*/  md; } ;
struct header_file_location {int dummy; } ;

/* Variables and functions */
 struct header_file_location* bincl_list ; 
 int bincls_allocated ; 
 struct header_file_location* next_bincl ; 
 scalar_t__ xmmalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_bincl_list (int number, struct objfile *objfile)
{
  bincls_allocated = number;
  next_bincl = bincl_list = (struct header_file_location *)
    xmmalloc (objfile->md, bincls_allocated * sizeof (struct header_file_location));
}