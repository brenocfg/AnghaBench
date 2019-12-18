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
struct TYPE_2__ {int align; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peek () ; 
 TYPE_1__* read_cast_type () ; 
 int read_intexpr () ; 

__attribute__((used)) static int read_alignas() {
    // C11 6.7.5. Valid form of _Alignof is either _Alignas(type-name) or
    // _Alignas(constant-expression).
    expect('(');
    int r = is_type(peek())
        ? read_cast_type()->align
        : read_intexpr();
    expect(')');
    return r;
}