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
 int /*<<< orphan*/  java_demangled_signature_copy (char*,char*) ; 
 int java_demangled_signature_length (char*) ; 
 char* xmalloc (int) ; 

char *
java_demangle_type_signature (char *signature)
{
  int length = java_demangled_signature_length (signature);
  char *result = xmalloc (length + 1);
  java_demangled_signature_copy (result, signature);
  result[length] = '\0';
  return result;
}