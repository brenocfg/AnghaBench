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
#define  DT_SCORE_BASE_ADDRESS 133 
#define  DT_SCORE_GOTSYM 132 
#define  DT_SCORE_HIPAGENO 131 
#define  DT_SCORE_LOCAL_GOTNO 130 
#define  DT_SCORE_SYMTABNO 129 
#define  DT_SCORE_UNREFEXTNO 128 

__attribute__((used)) static const char *
get_score_dynamic_type (unsigned long type)
{
  switch (type)
    {
    case DT_SCORE_BASE_ADDRESS: return "SCORE_BASE_ADDRESS";
    case DT_SCORE_LOCAL_GOTNO:  return "SCORE_LOCAL_GOTNO";
    case DT_SCORE_SYMTABNO:     return "SCORE_SYMTABNO";
    case DT_SCORE_GOTSYM:       return "SCORE_GOTSYM";
    case DT_SCORE_UNREFEXTNO:   return "SCORE_UNREFEXTNO";
    case DT_SCORE_HIPAGENO:     return "SCORE_HIPAGENO";
    default:
      return NULL;
    }
}