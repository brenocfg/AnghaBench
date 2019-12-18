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
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ reloc_howto_type ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

unsigned int
bfd_get_reloc_size (reloc_howto_type *howto)
{
  switch (howto->size)
    {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 0;
    case 4: return 8;
    case 8: return 16;
    case -2: return 4;
    default: abort ();
    }
}