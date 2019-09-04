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

/* Variables and functions */
 int /*<<< orphan*/  alphaActivated ; 
 int /*<<< orphan*/  antiAliasingActivated ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  depthActivated ; 
 int result ; 
 scalar_t__ resultAA ; 
 scalar_t__ resultAlpha ; 
 scalar_t__ resultDepth ; 
 scalar_t__ resultStencil ; 
 int /*<<< orphan*/  stencilActivated ; 
 scalar_t__ testAlpha (int /*<<< orphan*/ ) ; 
 scalar_t__ testAntiAliasing (int /*<<< orphan*/ ) ; 
 scalar_t__ testDepth (int /*<<< orphan*/ ) ; 
 scalar_t__ testStencil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw() {
  if (!resultAA) resultAA = testAntiAliasing(antiAliasingActivated);
  assert(resultAA);
   
  if (!resultDepth) resultDepth = testDepth(depthActivated);
  assert(resultDepth);
  
  if (!resultStencil) resultStencil = testStencil(stencilActivated);
  assert(resultStencil);
  
  if (!resultAlpha) resultAlpha = testAlpha(alphaActivated);
  assert(resultAlpha);
  
  result = resultAA && resultDepth && resultStencil && resultAlpha;
}