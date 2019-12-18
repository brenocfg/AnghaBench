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
typedef  enum enum_made { ____Placeholder_enum_made } enum_made ;

/* Variables and functions */
#define  ABORTED 135 
#define  BEINGMADE 134 
#define  DEFERRED 133 
#define  ERROR 132 
#define  MADE 131 
#define  REQUESTED 130 
#define  UNMADE 129 
#define  UPTODATE 128 

__attribute__((used)) static const char *
made_name(enum enum_made made)
{
    switch (made) {
    case UNMADE:     return "unmade";
    case DEFERRED:   return "deferred";
    case REQUESTED:  return "requested";
    case BEINGMADE:  return "being made";
    case MADE:       return "made";
    case UPTODATE:   return "up-to-date";
    case ERROR:      return "error when made";
    case ABORTED:    return "aborted";
    default:         return "unknown enum_made value";
    }
}