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
typedef  enum amd64_reg_class { ____Placeholder_amd64_reg_class } amd64_reg_class ;

/* Variables and functions */
 int AMD64_COMPLEX_X87 ; 
 int AMD64_INTEGER ; 
 int AMD64_MEMORY ; 
 int AMD64_NO_CLASS ; 
 int AMD64_SSE ; 
 int AMD64_X87 ; 
 int AMD64_X87UP ; 

__attribute__((used)) static enum amd64_reg_class
amd64_merge_classes (enum amd64_reg_class class1, enum amd64_reg_class class2)
{
  /* Rule (a): If both classes are equal, this is the resulting class.  */
  if (class1 == class2)
    return class1;

  /* Rule (b): If one of the classes is NO_CLASS, the resulting class
     is the other class.  */
  if (class1 == AMD64_NO_CLASS)
    return class2;
  if (class2 == AMD64_NO_CLASS)
    return class1;

  /* Rule (c): If one of the classes is MEMORY, the result is MEMORY.  */
  if (class1 == AMD64_MEMORY || class2 == AMD64_MEMORY)
    return AMD64_MEMORY;

  /* Rule (d): If one of the classes is INTEGER, the result is INTEGER.  */
  if (class1 == AMD64_INTEGER || class2 == AMD64_INTEGER)
    return AMD64_INTEGER;

  /* Rule (e): If one of the classes is X87, X87UP, COMPLEX_X87 class,
     MEMORY is used as class.  */
  if (class1 == AMD64_X87 || class1 == AMD64_X87UP
      || class1 == AMD64_COMPLEX_X87 || class2 == AMD64_X87
      || class2 == AMD64_X87UP || class2 == AMD64_COMPLEX_X87)
    return AMD64_MEMORY;

  /* Rule (f): Otherwise class SSE is used.  */
  return AMD64_SSE;
}