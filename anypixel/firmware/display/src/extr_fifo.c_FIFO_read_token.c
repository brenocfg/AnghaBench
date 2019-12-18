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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int size; int free; int tail; char const* buffer; } ;
typedef  TYPE_1__ FIFO_Data_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_read (TYPE_1__*,int*,int) ; 

uint16_t FIFO_read_token(FIFO_Data_TypeDef *inStruct, uint8_t *outBytes, uint16_t max, const char *delimiters, uint8_t listLength) {
	int i, j, ptr, available, start;
	bool found;

	start = -1;

	available = inStruct->size - inStruct->free;
	if(available > max)
		available = max;
	ptr = inStruct->tail;
	for(i = 0; i < available; i++) {
        found = false;
		for(j = 0; j < listLength; j++) {
			if( inStruct->buffer[ptr] == delimiters[j] ) {
                // found something we are looking for so build the return string
                found = true;
			    if(start != -1) {
                    // discard the first bytes
                    if(start != 0)
                        FIFO_read( inStruct, outBytes, start );
                    // read the remaining non-delimiters (throw away ending delimiter by returning 1 less than bytes read)
			        FIFO_read( inStruct, outBytes, i+1-start );
                    return i-start;
			    }
			    break;
			}
		}
		if(!found && start == -1)
            start = i;

		ptr++;
		if(ptr >= inStruct->size)
			ptr = 0;
	}

	// cover the case where we didn't encounter a delimiter but have hit the max length
	if(i == max) {
		FIFO_read(inStruct, outBytes, i);
		return i;
	}
	return 0;
}