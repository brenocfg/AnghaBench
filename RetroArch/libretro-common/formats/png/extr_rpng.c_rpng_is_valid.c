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
struct TYPE_3__ {scalar_t__ has_iend; scalar_t__ has_idat; scalar_t__ has_ihdr; } ;
typedef  TYPE_1__ rpng_t ;

/* Variables and functions */

bool rpng_is_valid(rpng_t *rpng)
{
   /* A valid PNG image must contain an IHDR chunk,
    * one or more IDAT chunks, and an IEND chunk */
   if (rpng && rpng->has_ihdr && rpng->has_idat && rpng->has_iend)
      return true;

   return false;
}