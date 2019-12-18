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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void  supcon_puti( int num )
{
  int sign;
  int temp;
  char buffer[ 128 ];	// You're generous. 
  int position = 126;

  // Short circuit unnecessary work.
  if ( num == 0 ) 
  {
	fputs("0",stdout);
	return;
  }


  // Prepare to do work.
  if ( num < 0 )
  {
	sign = 1;
	temp = -num;
  }
  else
  {
	sign = 0;
	temp = num;
  }
  

  buffer[127] = 0;
  
  // Now reduce it.
  while ( temp > 0 )
  {
	buffer[ position-- ] = '0' + (temp % 10);
	temp = temp / 10;
  }
		  
  if ( sign == 1 ) buffer[ position-- ] = '-';
  
  // Now print it.
  fputs(buffer + position + 1 ,stdout);
}