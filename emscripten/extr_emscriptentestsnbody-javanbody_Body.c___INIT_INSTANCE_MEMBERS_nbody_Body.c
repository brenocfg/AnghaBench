#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mass_; scalar_t__ vz_; scalar_t__ vy_; scalar_t__ vx_; scalar_t__ z_; scalar_t__ y_; scalar_t__ x_; } ;
struct TYPE_5__ {TYPE_1__ nbody_Body; } ;
struct TYPE_6__ {TYPE_2__ fields; } ;
typedef  TYPE_3__ nbody_Body ;
typedef  scalar_t__ JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  __INIT_INSTANCE_MEMBERS_java_lang_Object (scalar_t__,int) ; 

void __INIT_INSTANCE_MEMBERS_nbody_Body(JAVA_OBJECT me, int derivedClassWillRegisterFinalizer)
{
    __INIT_INSTANCE_MEMBERS_java_lang_Object(me, 0 || derivedClassWillRegisterFinalizer);
    ((nbody_Body*) me)->fields.nbody_Body.x_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.y_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.z_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.vx_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.vy_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.vz_ = 0;
    ((nbody_Body*) me)->fields.nbody_Body.mass_ = 0;
    //XMLVM_BEGIN_WRAPPER[__INIT_INSTANCE_MEMBERS_nbody_Body]
    //XMLVM_END_WRAPPER
}