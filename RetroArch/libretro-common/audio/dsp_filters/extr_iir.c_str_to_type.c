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
typedef  enum IIRFilter { ____Placeholder_IIRFilter } IIRFilter ;

/* Variables and functions */
 int APF ; 
 int BBOOST ; 
 int BPCSGF ; 
 int BPZPGF ; 
 int /*<<< orphan*/  CHECK (int) ; 
 int HPF ; 
 int HSH ; 
 int LPF ; 
 int LSH ; 
 int NOTCH ; 
 int PEQ ; 
 int RIAA_CD ; 
 int RIAA_phono ; 

__attribute__((used)) static enum IIRFilter str_to_type(const char *str)
{
   CHECK(LPF);
   CHECK(HPF);
   CHECK(BPCSGF);
   CHECK(BPZPGF);
   CHECK(APF);
   CHECK(NOTCH);
   CHECK(RIAA_phono);
   CHECK(PEQ);
   CHECK(BBOOST);
   CHECK(LSH);
   CHECK(HSH);
   CHECK(RIAA_CD);

   return LPF; /* Fallback. */
}