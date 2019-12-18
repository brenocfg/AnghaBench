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
typedef  int /*<<< orphan*/  static_codebook ;
struct TYPE_3__ {int books; int /*<<< orphan*/  const** book_param; } ;
typedef  TYPE_1__ codec_setup_info ;

/* Variables and functions */

__attribute__((used)) static int book_dup_or_new(codec_setup_info *ci,const static_codebook *book){
  int i;
  for(i=0;i<ci->books;i++)
    if(ci->book_param[i]==book)return(i);

  return(ci->books++);
}