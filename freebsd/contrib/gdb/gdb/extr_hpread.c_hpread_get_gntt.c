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
typedef  union dnttentry {int dummy; } dnttentry ;
struct objfile {int dummy; } ;
struct dntt_type_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GNTT (struct objfile*) ; 

__attribute__((used)) static union dnttentry *
hpread_get_gntt (int index, struct objfile *objfile)
{
  return (union dnttentry *)
    &(GNTT (objfile)[(index * sizeof (struct dntt_type_block))]);
}