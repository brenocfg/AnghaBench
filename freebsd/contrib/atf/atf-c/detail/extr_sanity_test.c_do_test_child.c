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
struct test_data {int m_type; int /*<<< orphan*/  m_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
#define  inv 131 
#define  post 130 
#define  pre 129 
#define  unreachable 128 

__attribute__((used)) static
void
do_test_child(void *v)
{
    struct test_data *td = v;

    switch (td->m_type) {
    case inv:
        INV(td->m_cond);
        break;

    case pre:
        PRE(td->m_cond);
        break;

    case post:
        POST(td->m_cond);
        break;

    case unreachable:
        if (!td->m_cond)
            UNREACHABLE;
        break;
    }

    exit(EXIT_SUCCESS);
}