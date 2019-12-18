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
 int /*<<< orphan*/  FEATURE_AVX512VNNI ; 
 unsigned int INTEL_BONNELL ; 
 unsigned int INTEL_CORE2 ; 
 unsigned int INTEL_COREI7 ; 
 unsigned int INTEL_COREI7_BROADWELL ; 
 unsigned int INTEL_COREI7_CANNONLAKE ; 
 unsigned int INTEL_COREI7_CASCADELAKE ; 
 unsigned int INTEL_COREI7_HASWELL ; 
 unsigned int INTEL_COREI7_ICELAKE_CLIENT ; 
 unsigned int INTEL_COREI7_ICELAKE_SERVER ; 
 unsigned int INTEL_COREI7_IVYBRIDGE ; 
 unsigned int INTEL_COREI7_NEHALEM ; 
 unsigned int INTEL_COREI7_SANDYBRIDGE ; 
 unsigned int INTEL_COREI7_SKYLAKE ; 
 unsigned int INTEL_COREI7_SKYLAKE_AVX512 ; 
 unsigned int INTEL_COREI7_WESTMERE ; 
 unsigned int INTEL_GOLDMONT ; 
 unsigned int INTEL_GOLDMONT_PLUS ; 
 unsigned int INTEL_KNL ; 
 unsigned int INTEL_KNM ; 
 unsigned int INTEL_SILVERMONT ; 
 unsigned int INTEL_TREMONT ; 

__attribute__((used)) static void getIntelProcessorTypeAndSubtype(unsigned Family, unsigned Model,
                                            unsigned Brand_id,
                                            unsigned Features,
                                            unsigned Features2, unsigned *Type,
                                            unsigned *Subtype) {
  if (Brand_id != 0)
    return;
  switch (Family) {
  case 6:
    switch (Model) {
    case 0x0f: // Intel Core 2 Duo processor, Intel Core 2 Duo mobile
               // processor, Intel Core 2 Quad processor, Intel Core 2 Quad
               // mobile processor, Intel Core 2 Extreme processor, Intel
               // Pentium Dual-Core processor, Intel Xeon processor, model
               // 0Fh. All processors are manufactured using the 65 nm process.
    case 0x16: // Intel Celeron processor model 16h. All processors are
               // manufactured using the 65 nm process
    case 0x17: // Intel Core 2 Extreme processor, Intel Xeon processor, model
               // 17h. All processors are manufactured using the 45 nm process.
               //
               // 45nm: Penryn , Wolfdale, Yorkfield (XE)
    case 0x1d: // Intel Xeon processor MP. All processors are manufactured using
               // the 45 nm process.
      *Type = INTEL_CORE2; // "penryn"
      break;
    case 0x1a: // Intel Core i7 processor and Intel Xeon processor. All
               // processors are manufactured using the 45 nm process.
    case 0x1e: // Intel(R) Core(TM) i7 CPU         870  @ 2.93GHz.
               // As found in a Summer 2010 model iMac.
    case 0x1f:
    case 0x2e:              // Nehalem EX
      *Type = INTEL_COREI7; // "nehalem"
      *Subtype = INTEL_COREI7_NEHALEM;
      break;
    case 0x25: // Intel Core i7, laptop version.
    case 0x2c: // Intel Core i7 processor and Intel Xeon processor. All
               // processors are manufactured using the 32 nm process.
    case 0x2f: // Westmere EX
      *Type = INTEL_COREI7; // "westmere"
      *Subtype = INTEL_COREI7_WESTMERE;
      break;
    case 0x2a: // Intel Core i7 processor. All processors are manufactured
               // using the 32 nm process.
    case 0x2d:
      *Type = INTEL_COREI7; //"sandybridge"
      *Subtype = INTEL_COREI7_SANDYBRIDGE;
      break;
    case 0x3a:
    case 0x3e:              // Ivy Bridge EP
      *Type = INTEL_COREI7; // "ivybridge"
      *Subtype = INTEL_COREI7_IVYBRIDGE;
      break;

    // Haswell:
    case 0x3c:
    case 0x3f:
    case 0x45:
    case 0x46:
      *Type = INTEL_COREI7; // "haswell"
      *Subtype = INTEL_COREI7_HASWELL;
      break;

    // Broadwell:
    case 0x3d:
    case 0x47:
    case 0x4f:
    case 0x56:
      *Type = INTEL_COREI7; // "broadwell"
      *Subtype = INTEL_COREI7_BROADWELL;
      break;

    // Skylake:
    case 0x4e:              // Skylake mobile
    case 0x5e:              // Skylake desktop
    case 0x8e:              // Kaby Lake mobile
    case 0x9e:              // Kaby Lake desktop
      *Type = INTEL_COREI7; // "skylake"
      *Subtype = INTEL_COREI7_SKYLAKE;
      break;

    // Skylake Xeon:
    case 0x55:
      *Type = INTEL_COREI7;
      if (Features2 & (1 << (FEATURE_AVX512VNNI - 32)))
        *Subtype = INTEL_COREI7_CASCADELAKE; // "cascadelake"
      else
        *Subtype = INTEL_COREI7_SKYLAKE_AVX512; // "skylake-avx512"
      break;

    // Cannonlake:
    case 0x66:
      *Type = INTEL_COREI7;
      *Subtype = INTEL_COREI7_CANNONLAKE; // "cannonlake"
      break;

    // Icelake:
    case 0x7d:
    case 0x7e:
      *Type = INTEL_COREI7;
      *Subtype = INTEL_COREI7_ICELAKE_CLIENT; // "icelake-client"
      break;

    // Icelake Xeon:
    case 0x6a:
    case 0x6c:
      *Type = INTEL_COREI7;
      *Subtype = INTEL_COREI7_ICELAKE_SERVER; // "icelake-server"
      break;

    case 0x1c: // Most 45 nm Intel Atom processors
    case 0x26: // 45 nm Atom Lincroft
    case 0x27: // 32 nm Atom Medfield
    case 0x35: // 32 nm Atom Midview
    case 0x36: // 32 nm Atom Midview
      *Type = INTEL_BONNELL;
      break; // "bonnell"

    // Atom Silvermont codes from the Intel software optimization guide.
    case 0x37:
    case 0x4a:
    case 0x4d:
    case 0x5a:
    case 0x5d:
    case 0x4c: // really airmont
      *Type = INTEL_SILVERMONT;
      break; // "silvermont"
    // Goldmont:
    case 0x5c: // Apollo Lake
    case 0x5f: // Denverton
      *Type = INTEL_GOLDMONT;
      break; // "goldmont"
    case 0x7a:
      *Type = INTEL_GOLDMONT_PLUS;
      break;
    case 0x86:
      *Type = INTEL_TREMONT;
      break;

    case 0x57:
      *Type = INTEL_KNL; // knl
      break;

    case 0x85:
      *Type = INTEL_KNM; // knm
      break;

    default: // Unknown family 6 CPU.
      break;
      break;
    }
  default:
    break; // Unknown.
  }
}