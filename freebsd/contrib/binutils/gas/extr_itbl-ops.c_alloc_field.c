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
struct TYPE_2__ {int sbit; int ebit; } ;
struct itbl_field {unsigned long flags; TYPE_1__ range; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  e_type ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct itbl_field*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct itbl_field *
alloc_field (e_type type, int sbit, int ebit,
	     unsigned long flags)
{
  struct itbl_field *f;
  f = (struct itbl_field *) malloc (sizeof (struct itbl_field));
  if (f)
    {
      memset (f, 0, sizeof (struct itbl_field));
      f->type = type;
      f->range.sbit = sbit;
      f->range.ebit = ebit;
      f->flags = flags;
    }
  return f;
}