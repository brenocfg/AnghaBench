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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  COMPLEX_CST 131 
#define  INTEGER_CST 130 
#define  REAL_CST 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  VECTOR_CST 128 
 int native_encode_complex (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int native_encode_int (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int native_encode_real (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int native_encode_vector (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
native_encode_expr (tree expr, unsigned char *ptr, int len)
{
  switch (TREE_CODE (expr))
    {
    case INTEGER_CST:
      return native_encode_int (expr, ptr, len);

    case REAL_CST:
      return native_encode_real (expr, ptr, len);

    case COMPLEX_CST:
      return native_encode_complex (expr, ptr, len);

    case VECTOR_CST:
      return native_encode_vector (expr, ptr, len);

    default:
      return 0;
    }
}