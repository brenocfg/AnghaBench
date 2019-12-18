#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; char* buffer; int /*<<< orphan*/  storage; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_INCREMENT ; 
 char* _ogg_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void oggpack_writeinit(oggpack_buffer *b){
  memset(b,0,sizeof(*b));
  b->ptr=b->buffer=_ogg_malloc(BUFFER_INCREMENT);
  b->buffer[0]='\0';
  b->storage=BUFFER_INCREMENT;
}