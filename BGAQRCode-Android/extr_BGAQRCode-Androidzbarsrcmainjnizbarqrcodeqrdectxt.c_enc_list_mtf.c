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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */

__attribute__((used)) static void enc_list_mtf(iconv_t _enc_list[3],iconv_t _enc){
  int i;
  for(i=0;i<3;i++)if(_enc_list[i]==_enc){
    int j;
    for(j=i;j-->0;)_enc_list[j+1]=_enc_list[j];
    _enc_list[0]=_enc;
    break;
  }
}