#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oggbyte_buffer ;
struct TYPE_3__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */
 int /*<<< orphan*/  oggbyte_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int oggbyte_read1 (int /*<<< orphan*/ *,int) ; 

int ogg_page_packets(ogg_page *og){
  int i;
  int n;
  int count=0;
  oggbyte_buffer ob;
  oggbyte_init(&ob,og->header);

  n=oggbyte_read1(&ob,26);
  for(i=0;i<n;i++)
    if(oggbyte_read1(&ob,27+i)<255)count++;
  return(count);
}