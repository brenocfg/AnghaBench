#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ Dict ;

/* Variables and functions */
 int /*<<< orphan*/  make_map () ; 
 int /*<<< orphan*/  make_vector () ; 
 TYPE_1__* malloc (int) ; 

Dict *make_dict() {
    Dict *r = malloc(sizeof(Dict));
    r->map = make_map();
    r->key = make_vector();
    return r;
}