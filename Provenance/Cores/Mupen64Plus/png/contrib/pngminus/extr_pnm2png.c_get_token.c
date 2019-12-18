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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 

void get_token(FILE *pnm_file, char *token)
{
  int i = 0;
  int ret;

  /* remove white-space and comment lines */
  do
  {
    ret = fgetc(pnm_file);
    if (ret == '#') {
      /* the rest of this line is a comment */
      do
      {
        ret = fgetc(pnm_file);
      }
      while ((ret != '\n') && (ret != '\r') && (ret != EOF));
    }
    if (ret == EOF) break;
    token[i] = (unsigned char) ret;
  }
  while ((token[i] == '\n') || (token[i] == '\r') || (token[i] == ' '));

  /* read string */
  do
  {
    ret = fgetc(pnm_file);
    if (ret == EOF) break;
    i++;
    token[i] = (unsigned char) ret;
  }
  while ((token[i] != '\n') && (token[i] != '\r') && (token[i] != ' '));

  token[i] = '\0';

  return;
}