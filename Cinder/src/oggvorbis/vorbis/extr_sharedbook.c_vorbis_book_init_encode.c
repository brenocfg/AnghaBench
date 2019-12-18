#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  q_delta; int /*<<< orphan*/  q_min; int /*<<< orphan*/  entries; int /*<<< orphan*/  lengthlist; int /*<<< orphan*/  dim; } ;
typedef  TYPE_1__ static_codebook ;
struct TYPE_8__ {int minval; int delta; int /*<<< orphan*/  quantvals; int /*<<< orphan*/  codelist; int /*<<< orphan*/  dim; int /*<<< orphan*/  used_entries; int /*<<< orphan*/  entries; TYPE_1__ const* c; } ;
typedef  TYPE_2__ codebook ;

/* Variables and functions */
 int /*<<< orphan*/  _book_maptype1_quantvals (TYPE_1__ const*) ; 
 int /*<<< orphan*/  _float32_unpack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _make_words (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rint (int /*<<< orphan*/ ) ; 

int vorbis_book_init_encode(codebook *c,const static_codebook *s){

  memset(c,0,sizeof(*c));
  c->c=s;
  c->entries=s->entries;
  c->used_entries=s->entries;
  c->dim=s->dim;
  c->codelist=_make_words(s->lengthlist,s->entries,0);
  //c->valuelist=_book_unquantize(s,s->entries,NULL);
  c->quantvals=_book_maptype1_quantvals(s);
  c->minval=(int)rint(_float32_unpack(s->q_min));
  c->delta=(int)rint(_float32_unpack(s->q_delta));

  return(0);
}