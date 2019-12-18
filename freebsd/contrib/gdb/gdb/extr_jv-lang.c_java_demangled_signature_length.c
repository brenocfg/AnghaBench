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
 char* TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_primitive_type (char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
java_demangled_signature_length (char *signature)
{
  int array = 0;
  for (; *signature == '['; signature++)
    array += 2;			/* Two chars for "[]". */
  switch (signature[0])
    {
    case 'L':
      /* Subtract 2 for 'L' and ';'. */
      return strlen (signature) - 2 + array;
    default:
      return strlen (TYPE_NAME (java_primitive_type (signature[0]))) + array;
    }
}