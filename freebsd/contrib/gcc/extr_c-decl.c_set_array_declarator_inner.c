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
struct c_declarator {struct c_declarator* declarator; } ;

/* Variables and functions */

struct c_declarator *
set_array_declarator_inner (struct c_declarator *decl,
			    struct c_declarator *inner,
			    bool abstract_p __attribute__ ((__unused__)))
{
  decl->declarator = inner;
  return decl;
}