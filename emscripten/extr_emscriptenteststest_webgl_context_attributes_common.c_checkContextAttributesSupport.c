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
 int /*<<< orphan*/  EM_ASM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out (char) ; 
 int resultAA ; 
 int resultAlpha ; 
 int resultDepth ; 
 int resultStencil ; 
 int /*<<< orphan*/  webglAlphaSupported () ; 
 int /*<<< orphan*/  webglAntialiasSupported () ; 
 int /*<<< orphan*/  webglDepthSupported () ; 
 int /*<<< orphan*/  webglStencilSupported () ; 

__attribute__((used)) static void checkContextAttributesSupport() {
  if (!webglAntialiasSupported()) {
    resultAA = true;
    EM_ASM(out('warning: no antialiasing\n'));
  }
  if (!webglDepthSupported()) {
    resultDepth = true;
    EM_ASM(out('warning: no depth\n'));
  }
  if (!webglStencilSupported()) {
    resultStencil = true;
    EM_ASM(out('warning: no stencil\n'));
  }
  if (!webglAlphaSupported()) {
    resultAlpha = true;
    EM_ASM(out('warning: no alpha\n'));
  }
}