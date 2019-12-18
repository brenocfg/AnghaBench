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
struct nouveau_therm {int dummy; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int _nouveau_therm_init (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv40_sensor_setup (struct nouveau_therm*) ; 

__attribute__((used)) static int
nv40_therm_init(struct nouveau_object *object)
{
	struct nouveau_therm *therm = (void *)object;

	nv40_sensor_setup(therm);

	return _nouveau_therm_init(object);
}