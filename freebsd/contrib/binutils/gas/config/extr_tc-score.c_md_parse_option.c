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
#define  OPTION_EB 138 
#define  OPTION_EL 137 
#define  OPTION_FIXDD 136 
#define  OPTION_NWARN 135 
#define  OPTION_O0 134 
#define  OPTION_PIC 133 
#define  OPTION_R1 132 
#define  OPTION_SCORE5 131 
#define  OPTION_SCORE5U 130 
#define  OPTION_SCORE7 129 
#define  OPTION_SCORE_VERSION 128 
 int /*<<< orphan*/  PIC ; 
 int /*<<< orphan*/  SCORE5_PIPELINE ; 
 int /*<<< orphan*/  SCORE7_PIPELINE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int fix_data_dependency ; 
 int /*<<< orphan*/  g_opt ; 
 int /*<<< orphan*/  g_switch_value ; 
 int /*<<< orphan*/  nor1 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int score7 ; 
 int /*<<< orphan*/  score_pic ; 
 int target_big_endian ; 
 int university_version ; 
 int /*<<< orphan*/  vector_size ; 
 int /*<<< orphan*/  warn_fix_data_dependency ; 

int
md_parse_option (int c, char *arg)
{
  switch (c)
    {
#ifdef OPTION_EB
    case OPTION_EB:
      target_big_endian = 1;
      break;
#endif
#ifdef OPTION_EL
    case OPTION_EL:
      target_big_endian = 0;
      break;
#endif
    case OPTION_FIXDD:
      fix_data_dependency = 1;
      break;
    case OPTION_NWARN:
      warn_fix_data_dependency = 0;
      break;
    case OPTION_SCORE5:
      score7 = 0;
      university_version = 0;
      vector_size = SCORE5_PIPELINE;
      break;
    case OPTION_SCORE5U:
      score7 = 0;
      university_version = 1;
      vector_size = SCORE5_PIPELINE;
      break;
    case OPTION_SCORE7:
      score7 = 1;
      university_version = 0;
      vector_size = SCORE7_PIPELINE;
      break;
    case OPTION_R1:
      nor1 = 0;
      break;
    case 'G':
      g_switch_value = atoi (arg);
      break;
    case OPTION_O0:
      g_opt = 0;
      break;
    case OPTION_SCORE_VERSION:
      printf (_("Sunplus-v2-0-0-20060510\n"));
      break;
    case OPTION_PIC:
      score_pic = PIC;
      g_switch_value = 0;    /* Must set -G num as 0 to generate PIC code.  */
      break;
    default:
      /* as_bad (_("unrecognized option `-%c%s'"), c, arg ? arg : "");  */
      return 0;
    }
  return 1;
}