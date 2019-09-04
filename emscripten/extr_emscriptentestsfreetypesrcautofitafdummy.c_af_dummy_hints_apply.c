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
typedef  int /*<<< orphan*/  FT_Outline ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/ * AF_ScriptMetrics ;
typedef  int /*<<< orphan*/ * AF_GlyphHints ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Error
  af_dummy_hints_apply( AF_GlyphHints  hints,
                        FT_Outline*    outline,
                        AF_ScriptMetrics  metrics ) /* XXX EMSCRIPTEN */
  {
    FT_UNUSED( hints );
    FT_UNUSED( outline );
    FT_UNUSED( metrics ); /* XXX EMSCRIPTEN */

    return 0;
  }