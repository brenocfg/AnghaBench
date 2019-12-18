#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; scalar_t__ size; } ;
struct neon_typed_alias {int defined; scalar_t__ index; TYPE_1__ eltype; } ;

/* Variables and functions */
 int NTA_HASINDEX ; 
 int NTA_HASTYPE ; 

__attribute__((used)) static int
neon_alias_types_same (struct neon_typed_alias *a, struct neon_typed_alias *b)
{
  if (!a && !b)
    return 1;
    
  if (!a || !b)
    return 0;

  if (a->defined != b->defined)
    return 0;
  
  if ((a->defined & NTA_HASTYPE) != 0
      && (a->eltype.type != b->eltype.type
          || a->eltype.size != b->eltype.size))
    return 0;

  if ((a->defined & NTA_HASINDEX) != 0
      && (a->index != b->index))
    return 0;
  
  return 1;
}