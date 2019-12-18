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
 unsigned int AMDFAM10H ; 
 unsigned int AMDFAM10H_BARCELONA ; 
 unsigned int AMDFAM10H_ISTANBUL ; 
 unsigned int AMDFAM10H_SHANGHAI ; 
 unsigned int AMDFAM15H ; 
 unsigned int AMDFAM15H_BDVER1 ; 
 unsigned int AMDFAM15H_BDVER2 ; 
 unsigned int AMDFAM15H_BDVER3 ; 
 unsigned int AMDFAM15H_BDVER4 ; 
 unsigned int AMDFAM17H ; 
 unsigned int AMDFAM17H_ZNVER1 ; 
 unsigned int AMDFAM17H_ZNVER2 ; 
 unsigned int AMD_BTVER1 ; 
 unsigned int AMD_BTVER2 ; 

__attribute__((used)) static void getAMDProcessorTypeAndSubtype(unsigned Family, unsigned Model,
                                          unsigned Features, unsigned Features2,
                                          unsigned *Type, unsigned *Subtype) {
  // FIXME: this poorly matches the generated SubtargetFeatureKV table.  There
  // appears to be no way to generate the wide variety of AMD-specific targets
  // from the information returned from CPUID.
  switch (Family) {
  case 16:
    *Type = AMDFAM10H; // "amdfam10"
    switch (Model) {
    case 2:
      *Subtype = AMDFAM10H_BARCELONA;
      break;
    case 4:
      *Subtype = AMDFAM10H_SHANGHAI;
      break;
    case 8:
      *Subtype = AMDFAM10H_ISTANBUL;
      break;
    }
    break;
  case 20:
    *Type = AMD_BTVER1;
    break; // "btver1";
  case 21:
    *Type = AMDFAM15H;
    if (Model >= 0x60 && Model <= 0x7f) {
      *Subtype = AMDFAM15H_BDVER4;
      break; // "bdver4"; 60h-7Fh: Excavator
    }
    if (Model >= 0x30 && Model <= 0x3f) {
      *Subtype = AMDFAM15H_BDVER3;
      break; // "bdver3"; 30h-3Fh: Steamroller
    }
    if ((Model >= 0x10 && Model <= 0x1f) || Model == 0x02) {
      *Subtype = AMDFAM15H_BDVER2;
      break; // "bdver2"; 02h, 10h-1Fh: Piledriver
    }
    if (Model <= 0x0f) {
      *Subtype = AMDFAM15H_BDVER1;
      break; // "bdver1"; 00h-0Fh: Bulldozer
    }
    break;
  case 22:
    *Type = AMD_BTVER2;
    break; // "btver2"
  case 23:
    *Type = AMDFAM17H;
    if (Model >= 0x30 && Model <= 0x3f) {
      *Subtype = AMDFAM17H_ZNVER2;
      break; // "znver2"; 30h-3fh: Zen2
    }
    if (Model <= 0x0f) {
      *Subtype = AMDFAM17H_ZNVER1;
      break; // "znver1"; 00h-0Fh: Zen1
    }
    break;
  default:
    break; // "generic"
  }
}