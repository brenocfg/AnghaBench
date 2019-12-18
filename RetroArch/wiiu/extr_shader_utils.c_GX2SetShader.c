#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ program; } ;
struct TYPE_4__ {TYPE_3__ gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  ps; int /*<<< orphan*/  vs; } ;
typedef  TYPE_1__ GX2Shader ;

/* Variables and functions */
 int /*<<< orphan*/  GX2SetFetchShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX2SetGeometryShader (TYPE_3__*) ; 
 int /*<<< orphan*/  GX2SetPixelShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GX2SetVertexShader (int /*<<< orphan*/ *) ; 

void GX2SetShader(GX2Shader *shader)
{
   GX2SetVertexShader(&shader->vs);
   GX2SetPixelShader(&shader->ps);
   GX2SetFetchShader(&shader->fs);

   if (shader->gs.program)
      GX2SetGeometryShader(&shader->gs);
}