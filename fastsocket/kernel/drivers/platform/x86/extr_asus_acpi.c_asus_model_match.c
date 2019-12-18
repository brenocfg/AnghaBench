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
 int A1x ; 
 int A2x ; 
 int A4G ; 
 int A4S ; 
 int D1x ; 
 int END_MODEL ; 
 int F3Sa ; 
 int L2D ; 
 int L3C ; 
 int L3D ; 
 int L3H ; 
 int L4R ; 
 int L5x ; 
 int L8L ; 
 int M1A ; 
 int M2E ; 
 int M6N ; 
 int M6R ; 
 int R1F ; 
 int S1x ; 
 int S2x ; 
 int W1N ; 
 int W3V ; 
 int W5A ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int xxN ; 

__attribute__((used)) static int asus_model_match(char *model)
{
	if (model == NULL)
		return END_MODEL;

	if (strncmp(model, "L3D", 3) == 0)
		return L3D;
	else if (strncmp(model, "L2E", 3) == 0 ||
		 strncmp(model, "L3H", 3) == 0 || strncmp(model, "L5D", 3) == 0)
		return L3H;
	else if (strncmp(model, "L3", 2) == 0 || strncmp(model, "L2B", 3) == 0)
		return L3C;
	else if (strncmp(model, "L8L", 3) == 0)
		return L8L;
	else if (strncmp(model, "L4R", 3) == 0)
		return L4R;
	else if (strncmp(model, "M6N", 3) == 0 || strncmp(model, "W3N", 3) == 0)
		return M6N;
	else if (strncmp(model, "M6R", 3) == 0 || strncmp(model, "A3G", 3) == 0)
		return M6R;
	else if (strncmp(model, "M2N", 3) == 0 ||
		 strncmp(model, "M3N", 3) == 0 ||
		 strncmp(model, "M5N", 3) == 0 ||
		 strncmp(model, "M6N", 3) == 0 ||
		 strncmp(model, "S1N", 3) == 0 ||
		 strncmp(model, "S5N", 3) == 0 || strncmp(model, "W1N", 3) == 0)
		return xxN;
	else if (strncmp(model, "M1", 2) == 0)
		return M1A;
	else if (strncmp(model, "M2", 2) == 0 || strncmp(model, "L4E", 3) == 0)
		return M2E;
	else if (strncmp(model, "L2", 2) == 0)
		return L2D;
	else if (strncmp(model, "L8", 2) == 0)
		return S1x;
	else if (strncmp(model, "D1", 2) == 0)
		return D1x;
	else if (strncmp(model, "A1", 2) == 0)
		return A1x;
	else if (strncmp(model, "A2", 2) == 0)
		return A2x;
	else if (strncmp(model, "J1", 2) == 0)
		return S2x;
	else if (strncmp(model, "L5", 2) == 0)
		return L5x;
	else if (strncmp(model, "A4G", 3) == 0)
		return A4G;
	else if (strncmp(model, "W1N", 3) == 0)
		return W1N;
	else if (strncmp(model, "W3V", 3) == 0)
		return W3V;
	else if (strncmp(model, "W5A", 3) == 0)
		return W5A;
	else if (strncmp(model, "R1F", 3) == 0)
		return R1F;
	else if (strncmp(model, "A4S", 3) == 0)
		return A4S;
	else if (strncmp(model, "F3Sa", 4) == 0)
		return F3Sa;
	else
		return END_MODEL;
}