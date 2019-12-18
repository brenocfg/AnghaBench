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
struct type {int dummy; } ;
typedef  double DOUBLEST ;

/* Variables and functions */
 char* fixed_type_info (struct type*) ; 
 int sscanf (char const*,char*,long*,long*) ; 

DOUBLEST
ada_delta (struct type *type)
{
  const char *encoding = fixed_type_info (type);
  long num, den;

  if (sscanf (encoding, "_%ld_%ld", &num, &den) < 2)
    return -1.0;
  else
    return (DOUBLEST) num / (DOUBLEST) den;
}