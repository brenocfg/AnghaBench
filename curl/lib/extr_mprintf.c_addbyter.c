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
struct nsprintf {scalar_t__ length; scalar_t__ max; unsigned char* buffer; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

__attribute__((used)) static int addbyter(int output, FILE *data)
{
  struct nsprintf *infop = (struct nsprintf *)data;
  unsigned char outc = (unsigned char)output;

  if(infop->length < infop->max) {
    /* only do this if we haven't reached max length yet */
    infop->buffer[0] = outc; /* store */
    infop->buffer++; /* increase pointer */
    infop->length++; /* we are now one byte larger */
    return outc;     /* fputc() returns like this on success */
  }
  return -1;
}