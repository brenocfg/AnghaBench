#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int MajorVersion; int MinorVersion; int /*<<< orphan*/  ContextProfile; int /*<<< orphan*/  ContextFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTRIB_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GLUT_COMPATIBILITY_PROFILE ; 
 int /*<<< orphan*/  GLUT_CORE_PROFILE ; 
 int /*<<< orphan*/  GLUT_DEBUG ; 
 int /*<<< orphan*/  GLUT_FORWARD_COMPATIBLE ; 
 int /*<<< orphan*/  GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_DEBUG_BIT_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_FLAGS_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_MAJOR_VERSION_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_MINOR_VERSION_ARB ; 
 int /*<<< orphan*/  GLX_CONTEXT_PROFILE_MASK_ARB ; 
 TYPE_1__ fgState ; 
 int /*<<< orphan*/  fghIsLegacyContextVersionRequested () ; 
 int fghMapBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fghFillContextAttributes( int *attributes ) {
  int where = 0, contextFlags, contextProfile;

  if ( !fghIsLegacyContextVersionRequested() ) {
    ATTRIB_VAL( GLX_CONTEXT_MAJOR_VERSION_ARB, fgState.MajorVersion );
    ATTRIB_VAL( GLX_CONTEXT_MINOR_VERSION_ARB, fgState.MinorVersion );
  }

  contextFlags =
    fghMapBit( fgState.ContextFlags, GLUT_DEBUG, GLX_CONTEXT_DEBUG_BIT_ARB ) |
    fghMapBit( fgState.ContextFlags, GLUT_FORWARD_COMPATIBLE, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB );
  if ( contextFlags != 0 ) {
    ATTRIB_VAL( GLX_CONTEXT_FLAGS_ARB, contextFlags );
  }

  contextProfile =
    fghMapBit( fgState.ContextProfile, GLUT_CORE_PROFILE, GLX_CONTEXT_CORE_PROFILE_BIT_ARB ) |
    fghMapBit( fgState.ContextProfile, GLUT_COMPATIBILITY_PROFILE, GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB );
  if ( contextProfile != 0 ) {
    ATTRIB_VAL( GLX_CONTEXT_PROFILE_MASK_ARB, contextProfile );
  }

  ATTRIB( 0 );
}