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
struct attack_method {int /*<<< orphan*/  func; int /*<<< orphan*/  vector; } ;
typedef  int /*<<< orphan*/  ATTACK_VECTOR ;
typedef  int /*<<< orphan*/  ATTACK_FUNC ;

/* Variables and functions */
 struct attack_method* calloc (int,int) ; 
 struct attack_method** methods ; 
 int methods_len ; 
 struct attack_method** realloc (struct attack_method**,int) ; 

__attribute__((used)) static void add_attack(ATTACK_VECTOR vector, ATTACK_FUNC func)
{
    struct attack_method *method = calloc(1, sizeof (struct attack_method));

    method->vector = vector;
    method->func = func;

    methods = realloc(methods, (methods_len + 1) * sizeof (struct attack_method *));
    methods[methods_len++] = method;
}