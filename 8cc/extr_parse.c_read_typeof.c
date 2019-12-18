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
typedef  int /*<<< orphan*/  Type ;
struct TYPE_2__ {int /*<<< orphan*/ * ty; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/ * read_cast_type () ; 
 TYPE_1__* read_comma_expr () ; 

__attribute__((used)) static Type *read_typeof() {
    expect('(');
    Type *r = is_type(peek())
        ? read_cast_type()
        : read_comma_expr()->ty;
    expect(')');
    return r;
}