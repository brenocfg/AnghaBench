#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int headbit; int headend; int* headptr; } ;
typedef  TYPE_1__ oggpack_buffer ;
typedef  int ogg_uint32_t ;

/* Variables and functions */
 scalar_t__ _halt_one (TYPE_1__*) ; 
 int /*<<< orphan*/  _span_one (TYPE_1__*) ; 
 unsigned long* mask ; 

long oggpack_read(oggpack_buffer *b,int bits){
  unsigned long m=mask[bits];
  ogg_uint32_t ret=-1;

  bits+=b->headbit;

  if(bits >= b->headend<<3){

    if(b->headend<0)return -1;
    
    if(bits){
      if (_halt_one(b)) return -1;
      ret=*b->headptr>>b->headbit;
      
      if(bits>=8){
        ++b->headptr;
        --b->headend;
        _span_one(b);
        if(bits>8){
          if (_halt_one(b)) return -1;
          ret|=*b->headptr<<(8-b->headbit);   
          
          if(bits>=16){
            ++b->headptr;
            --b->headend;
            _span_one(b);
            if(bits>16){
              if (_halt_one(b)) return -1;
              ret|=*b->headptr<<(16-b->headbit);  
              
              if(bits>=24){
                ++b->headptr;
                --b->headend;
                _span_one(b);
                if(bits>24){
                  if (_halt_one(b)) return -1;
                  ret|=*b->headptr<<(24-b->headbit);
                  
                  if(bits>=32){
                    ++b->headptr;
                    --b->headend;
                    _span_one(b);
                    if(bits>32){
                      if (_halt_one(b)) return -1;
                      if(b->headbit)ret|=*b->headptr<<(32-b->headbit);
                      
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }else{
  
    ret=b->headptr[0]>>b->headbit;
    if(bits>8){
      ret|=b->headptr[1]<<(8-b->headbit);  
      if(bits>16){
        ret|=b->headptr[2]<<(16-b->headbit);  
        if(bits>24){
          ret|=b->headptr[3]<<(24-b->headbit);  
          if(bits>32 && b->headbit){
            ret|=b->headptr[4]<<(32-b->headbit);
          }
        }
      }
    }
    
    b->headptr+=bits/8;
    b->headend-=bits/8;
  }

  ret&=m;
  b->headbit=bits&7;   
  return ret;
}