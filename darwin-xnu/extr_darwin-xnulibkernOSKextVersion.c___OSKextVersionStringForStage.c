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
typedef  int OSKextVersionStage ;

/* Variables and functions */
#define  kOSKextVersionStageAlpha 133 
#define  kOSKextVersionStageBeta 132 
#define  kOSKextVersionStageCandidate 131 
#define  kOSKextVersionStageDevelopment 130 
#define  kOSKextVersionStageInvalid 129 
#define  kOSKextVersionStageRelease 128 

__attribute__((used)) static const char *
__OSKextVersionStringForStage(OSKextVersionStage stage)
{
	switch (stage) {
		case kOSKextVersionStageInvalid:     return NULL;
		case kOSKextVersionStageDevelopment: return "d";
		case kOSKextVersionStageAlpha:       return "a";
		case kOSKextVersionStageBeta:        return "b";
		case kOSKextVersionStageCandidate:   return "f";
		case kOSKextVersionStageRelease:     return "";
	}
}