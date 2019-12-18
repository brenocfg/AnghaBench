#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sourceLoc; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  source_loc ; 

__attribute__((used)) static Node *make_ast(Node *tmpl) {
    Node *r = malloc(sizeof(Node));
    *r = *tmpl;
    r->sourceLoc = source_loc;
    return r;
}