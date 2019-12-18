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
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */
 int /*<<< orphan*/  base_of_encoded_value (unsigned char,struct _Unwind_Context*) ; 
 unsigned char const* read_encoded_value_with_base (unsigned char,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline const unsigned char *
read_encoded_value (struct _Unwind_Context *context, unsigned char encoding,
		    const unsigned char *p, _Unwind_Ptr *val)
{
  return read_encoded_value_with_base (encoding,
		base_of_encoded_value (encoding, context),
		p, val);
}