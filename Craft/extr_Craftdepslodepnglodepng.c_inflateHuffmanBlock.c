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
struct TYPE_4__ {size_t size; unsigned char* data; } ;
typedef  TYPE_1__ ucvector ;
typedef  int /*<<< orphan*/  HuffmanTree ;

/* Variables and functions */
 unsigned int* DISTANCEBASE ; 
 unsigned int* DISTANCEEXTRA ; 
 int /*<<< orphan*/  ERROR_BREAK (int) ; 
 unsigned int FIRST_LENGTH_CODE_INDEX ; 
 int /*<<< orphan*/  HuffmanTree_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HuffmanTree_init (int /*<<< orphan*/ *) ; 
 unsigned int LAST_LENGTH_CODE_INDEX ; 
 size_t* LENGTHBASE ; 
 unsigned int* LENGTHEXTRA ; 
 unsigned int getTreeInflateDynamic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,size_t*,size_t) ; 
 int /*<<< orphan*/  getTreeInflateFixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int huffmanDecodeSymbol (unsigned char const*,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ readBitsFromStream (size_t*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  ucvector_resize (TYPE_1__*,size_t) ; 

__attribute__((used)) static unsigned inflateHuffmanBlock(ucvector* out, const unsigned char* in, size_t* bp,
                                    size_t* pos, size_t inlength, unsigned btype)
{
  unsigned error = 0;
  HuffmanTree tree_ll; /*the huffman tree for literal and length codes*/
  HuffmanTree tree_d; /*the huffman tree for distance codes*/
  size_t inbitlength = inlength * 8;

  HuffmanTree_init(&tree_ll);
  HuffmanTree_init(&tree_d);

  if(btype == 1) getTreeInflateFixed(&tree_ll, &tree_d);
  else if(btype == 2) error = getTreeInflateDynamic(&tree_ll, &tree_d, in, bp, inlength);

  while(!error) /*decode all symbols until end reached, breaks at end code*/
  {
    /*code_ll is literal, length or end code*/
    unsigned code_ll = huffmanDecodeSymbol(in, bp, &tree_ll, inbitlength);
    if(code_ll <= 255) /*literal symbol*/
    {
      if((*pos) >= out->size)
      {
        /*reserve more room at once*/
        if(!ucvector_resize(out, ((*pos) + 1) * 2)) ERROR_BREAK(83 /*alloc fail*/);
      }
      out->data[(*pos)] = (unsigned char)(code_ll);
      (*pos)++;
    }
    else if(code_ll >= FIRST_LENGTH_CODE_INDEX && code_ll <= LAST_LENGTH_CODE_INDEX) /*length code*/
    {
      unsigned code_d, distance;
      unsigned numextrabits_l, numextrabits_d; /*extra bits for length and distance*/
      size_t start, forward, backward, length;

      /*part 1: get length base*/
      length = LENGTHBASE[code_ll - FIRST_LENGTH_CODE_INDEX];

      /*part 2: get extra bits and add the value of that to length*/
      numextrabits_l = LENGTHEXTRA[code_ll - FIRST_LENGTH_CODE_INDEX];
      if(*bp >= inbitlength) ERROR_BREAK(51); /*error, bit pointer will jump past memory*/
      length += readBitsFromStream(bp, in, numextrabits_l);

      /*part 3: get distance code*/
      code_d = huffmanDecodeSymbol(in, bp, &tree_d, inbitlength);
      if(code_d > 29)
      {
        if(code_ll == (unsigned)(-1)) /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
        {
          /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
          (10=no endcode, 11=wrong jump outside of tree)*/
          error = (*bp) > inlength * 8 ? 10 : 11;
        }
        else error = 18; /*error: invalid distance code (30-31 are never used)*/
        break;
      }
      distance = DISTANCEBASE[code_d];

      /*part 4: get extra bits from distance*/
      numextrabits_d = DISTANCEEXTRA[code_d];
      if(*bp >= inbitlength) ERROR_BREAK(51); /*error, bit pointer will jump past memory*/

      distance += readBitsFromStream(bp, in, numextrabits_d);

      /*part 5: fill in all the out[n] values based on the length and dist*/
      start = (*pos);
      if(distance > start) ERROR_BREAK(52); /*too long backward distance*/
      backward = start - distance;
      if((*pos) + length >= out->size)
      {
        /*reserve more room at once*/
        if(!ucvector_resize(out, ((*pos) + length) * 2)) ERROR_BREAK(83 /*alloc fail*/);
      }

      for(forward = 0; forward < length; forward++)
      {
        out->data[(*pos)] = out->data[backward];
        (*pos)++;
        backward++;
        if(backward >= start) backward = start - distance;
      }
    }
    else if(code_ll == 256)
    {
      break; /*end code, break the loop*/
    }
    else /*if(code == (unsigned)(-1))*/ /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
    {
      /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
      (10=no endcode, 11=wrong jump outside of tree)*/
      error = (*bp) > inlength * 8 ? 10 : 11;
      break;
    }
  }

  HuffmanTree_cleanup(&tree_ll);
  HuffmanTree_cleanup(&tree_d);

  return error;
}