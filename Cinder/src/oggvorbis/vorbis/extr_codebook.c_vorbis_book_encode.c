#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_5__ {TYPE_1__* c; int /*<<< orphan*/ * codelist; } ;
typedef  TYPE_2__ codebook ;
struct TYPE_4__ {int entries; int* lengthlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int vorbis_book_encode(codebook *book, int a, oggpack_buffer *b){
  if(a<0 || a>=book->c->entries)return(0);
  oggpack_write(b,book->codelist[a],book->c->lengthlist[a]);
  return(book->c->lengthlist[a]);
}