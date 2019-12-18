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
struct patch {int addr; int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  genie_decode (char const*,struct patch*) ; 
 int /*<<< orphan*/  hex_decode (char*,struct patch*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void decode(const char* code, struct patch* result)
{
  int len = strlen(code), i, j;
  char code_to_pass[16], *x;
  const char *ad, *da;
  int adl, dal;

  /* Initialize the result */
  result->addr = result->data = 0;

  /* Just assume 8 char long string to be Game Genie code */
  if (len == 8)
  {
    genie_decode(code, result);
    return;
  }

  /* If it's 9 chars long and the 5th is a hyphen, we have a Game Genie
   * code. */
    if(len == 9 && code[4] == '-')
    {
      /* Remove the hyphen and pass to genie_decode */
      code_to_pass[0] = code[0];
      code_to_pass[1] = code[1];
      code_to_pass[2] = code[2];
      code_to_pass[3] = code[3];
      code_to_pass[4] = code[5];
      code_to_pass[5] = code[6];
      code_to_pass[6] = code[7];
      code_to_pass[7] = code[8];
      code_to_pass[8] = '\0';
      genie_decode(code_to_pass, result);
      return;
    }

  /* Otherwise, we assume it's a hex code.
   * Find the colon so we know where address ends and data starts. If there's
   * no colon, then we haven't a code at all! */
  if(!(x = strchr(code, ':'))) goto bad_code;
  ad = code; da = x + 1; adl = x - code; dal = len - adl - 1;

  /* If a section is empty or too long, toss it */
  if(adl == 0 || adl > 6 || dal == 0 || dal > 4) goto bad_code;

  /* Pad the address with zeros, then fill it with the value */
  for(i = 0; i < (6 - adl); ++i) code_to_pass[i] = '0';
  for(j = 0; i < 6; ++i, ++j) code_to_pass[i] = ad[j];

  /* Do the same for data */
  for(i = 6; i < (10 - dal); ++i) code_to_pass[i] = '0';
  for(j = 0; i < 10; ++i, ++j) code_to_pass[i] = da[j];

  code_to_pass[10] = '\0';

  /* Decode and goodbye */
  hex_decode(code_to_pass, result);
  return;

bad_code:

  /* AGH! Invalid code! */
  result->data = result->addr = -1;
  return;
}