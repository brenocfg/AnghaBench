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
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  enum amd64_reg_class { ____Placeholder_amd64_reg_class } amd64_reg_class ;

/* Variables and functions */
 int AMD64_INTEGER ; 
 int AMD64_NO_CLASS ; 
 int AMD64_SSE ; 
 int AMD64_X87 ; 
 int AMD64_X87UP ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_ARRAY ; 
 int TYPE_CODE_ENUM ; 
 int TYPE_CODE_FLT ; 
 int TYPE_CODE_INT ; 
 int TYPE_CODE_PTR ; 
 int TYPE_CODE_REF ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  amd64_classify_aggregate (struct type*,int*) ; 

__attribute__((used)) static void
amd64_classify (struct type *type, enum amd64_reg_class class[2])
{
  enum type_code code = TYPE_CODE (type);
  int len = TYPE_LENGTH (type);

  class[0] = class[1] = AMD64_NO_CLASS;

  /* Arguments of types (signed and unsigned) _Bool, char, short, int,
     long, long long, and pointers are in the INTEGER class.  */
  if ((code == TYPE_CODE_INT || code == TYPE_CODE_ENUM
       || code == TYPE_CODE_PTR || code == TYPE_CODE_REF)
      && (len == 1 || len == 2 || len == 4 || len == 8))
    class[0] = AMD64_INTEGER;

  /* Arguments of types float, double and __m64 are in class SSE.  */
  else if (code == TYPE_CODE_FLT && (len == 4 || len == 8))
    /* FIXME: __m64 .  */
    class[0] = AMD64_SSE;

  /* Arguments of types __float128 and __m128 are split into two
     halves.  The least significant ones belong to class SSE, the most
     significant one to class SSEUP.  */
  /* FIXME: __float128, __m128.  */

  /* The 64-bit mantissa of arguments of type long double belongs to
     class X87, the 16-bit exponent plus 6 bytes of padding belongs to
     class X87UP.  */
  else if (code == TYPE_CODE_FLT && len == 16)
    /* Class X87 and X87UP.  */
    class[0] = AMD64_X87, class[1] = AMD64_X87UP;

  /* Aggregates.  */
  else if (code == TYPE_CODE_ARRAY || code == TYPE_CODE_STRUCT
	   || code == TYPE_CODE_UNION)
    amd64_classify_aggregate (type, class);
}