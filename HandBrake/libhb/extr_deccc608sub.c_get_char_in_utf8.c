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

__attribute__((used)) static int get_char_in_utf8(unsigned char *buffer, unsigned char c)
{
    if (c == 0x00)
        return 0;

    // Regular line-21 character set, mostly ASCII except these exceptions
    if (c < 0x80)
    {
        switch (c)
        {
        case 0x2a: // lowercase a, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0xa1;
            return 2;
        case 0x5c: // lowercase e, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0xa9;
            return 2;
        case 0x5e: // lowercase i, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0xad;
            return 2;
        case 0x5f: // lowercase o, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0xb3;
            return 2;
        case 0x60: // lowercase u, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0xba;
            return 2;
        case 0x7b: // lowercase c with cedilla
            *buffer = 0xc3;
            *(buffer+1) = 0xa7;
            return 2;
        case 0x7c: // division symbol
            *buffer = 0xc3;
            *(buffer+1) = 0xb7;
            return 2;
        case 0x7d: // uppercase N tilde
            *buffer = 0xc3;
            *(buffer+1) = 0x91;
            return 2;
        case 0x7e: // lowercase n tilde
            *buffer = 0xc3;
            *(buffer+1) = 0xb1;
            return 2;
        default:
            *buffer = c;
            return 1;
        }
    }
    switch (c)
    {
        // THIS BLOCK INCLUDES THE 16 EXTENDED (TWO-BYTE) LINE 21 CHARACTERS
        // THAT COME FROM HI BYTE = 0x11 AND LOW BETWEEN 0x30 AND 0x3F
        case 0x80: // Registered symbol (R)
            *buffer = 0xc2;
            *(buffer+1) = 0xae;
            return 2;
        case 0x81: // degree sign
            *buffer = 0xc2;
            *(buffer+1) = 0xb0;
            return 2;
        case 0x82: // 1/2 symbol
            *buffer = 0xc2;
            *(buffer+1) = 0xbd;
            return 2;
        case 0x83: // Inverted (open) question mark
            *buffer = 0xc2;
            *(buffer+1) = 0xbf;
            return 2;
        case 0x84: // Trademark symbol (TM)
            *buffer = 0xe2;
            *(buffer+1) = 0x84;
            *(buffer+2) = 0xa2;
            return 3;
        case 0x85: // Cents symbol
            *buffer = 0xc2;
            *(buffer+1) = 0xa2;
            return 2;
        case 0x86: // Pounds sterling
            *buffer = 0xc2;
            *(buffer+1) = 0xa3;
            return 2;
        case 0x87: // Music note
            *buffer = 0xe2;
            *(buffer+1) = 0x99;
            *(buffer+2) = 0xaa;
            return 3;
        case 0x88: // lowercase a, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0xa0;
            return 2;
        case 0x89: // transparent space, we make it regular
            *buffer = 0x20;
            return 1;
        case 0x8a: // lowercase e, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0xa8;
            return 2;
        case 0x8b: // lowercase a, circumflex accent
            *buffer = 0xc3;
            *(buffer+1) = 0xa2;
            return 2;
        case 0x8c: // lowercase e, circumflex accent
            *buffer = 0xc3;
            *(buffer+1) = 0xaa;
            return 2;
        case 0x8d: // lowercase i, circumflex accent
            *buffer = 0xc3;
            *(buffer+1) = 0xae;
            return 2;
        case 0x8e: // lowercase o, circumflex accent
            *buffer = 0xc3;
            *(buffer+1) = 0xb4;
            return 2;
        case 0x8f: // lowercase u, circumflex accent
            *buffer = 0xc3;
            *(buffer+1) = 0xbb;
            return 2;
        // THIS BLOCK INCLUDES THE 32 EXTENDED (TWO-BYTE) LINE 21 CHARACTERS
        // THAT COME FROM HI BYTE = 0x12 AND LOW BETWEEN 0x20 AND 0x3F
        case 0x90: // capital letter A with acute
            *buffer = 0xc3;
            *(buffer+1) = 0x81;
            return 2;
        case 0x91: // capital letter E with acute
            *buffer = 0xc3;
            *(buffer+1) = 0x89;
            return 2;
        case 0x92: // capital letter O with acute
            *buffer = 0xc3;
            *(buffer+1) = 0x93;
            return 2;
        case 0x93: // capital letter U with acute
            *buffer = 0xc3;
            *(buffer+1) = 0x9a;
            return 2;
        case 0x94: // capital letter U with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0x9c;
            return 2;
        case 0x95: // lowercase letter U with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0xbc;
            return 2;
        case 0x96: // apostrophe
            *buffer = 0x27;
            return 1;
        case 0x97: // inverted exclamation mark
            *buffer = 0xc2;
            *(buffer+1) = 0xa1;
            return 2;
        case 0x98: // asterisk
            *buffer = 0x2a;
            return 1;
        case 0x99: // apostrophe (yes, duped). See CCADI source code.
            *buffer = 0x27;
            return 1;
        case 0x9a: // hyphen-minus
            *buffer = 0x2d;
            return 1;
        case 0x9b: // copyright sign
            *buffer = 0xc2;
            *(buffer+1) = 0xa9;
            return 2;
        case 0x9c: // Service mark
            *buffer = 0xe2;
            *(buffer+1) = 0x84;
            *(buffer+2) = 0xa0;
            return 3;
        case 0x9d: // Full stop (.)
            *buffer = 0x2e;
            return 1;
        case 0x9e: // Quotation mark
            *buffer = 0x22;
            return 1;
        case 0x9f: // Quotation mark
            *buffer = 0x22;
            return 1;
        case 0xa0: // uppercase A, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0x80;
            return 2;
        case 0xa1: // uppercase A, circumflex
            *buffer = 0xc3;
            *(buffer+1) = 0x82;
            return 2;
        case 0xa2: // uppercase C with cedilla
            *buffer = 0xc3;
            *(buffer+1) = 0x87;
            return 2;
        case 0xa3: // uppercase E, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0x88;
            return 2;
        case 0xa4: // uppercase E, circumflex
            *buffer = 0xc3;
            *(buffer+1) = 0x8a;
            return 2;
        case 0xa5: // capital letter E with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0x8b;
            return 2;
        case 0xa6: // lowercase letter e with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0xab;
            return 2;
        case 0xa7: // uppercase I, circumflex
            *buffer = 0xc3;
            *(buffer+1) = 0x8e;
            return 2;
        case 0xa8: // uppercase I, with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0x8f;
            return 2;
        case 0xa9: // lowercase i, with diaeresis
            *buffer = 0xc3;
            *(buffer+1) = 0xaf;
            return 2;
        case 0xaa: // uppercase O, circumflex
            *buffer = 0xc3;
            *(buffer+1) = 0x94;
            return 2;
        case 0xab: // uppercase U, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0x99;
            return 2;
        case 0xac: // lowercase u, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0xb9;
            return 2;
        case 0xad: // uppercase U, circumflex
            *buffer = 0xc3;
            *(buffer+1) = 0x9b;
            return 2;
        case 0xae: // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
            *buffer = 0xc2;
            *(buffer+1) = 0xab;
            return 2;
        case 0xaf: // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
            *buffer = 0xc2;
            *(buffer+1) = 0xbb;
            return 2;
        // THIS BLOCK INCLUDES THE 32 EXTENDED (TWO-BYTE) LINE 21 CHARACTERS
        // THAT COME FROM HI BYTE = 0x13 AND LOW BETWEEN 0x20 AND 0x3F
        case 0xb0: // Uppercase A, tilde
            *buffer = 0xc3;
            *(buffer+1) = 0x83;
            return 2;
        case 0xb1: // Lowercase a, tilde
            *buffer = 0xc3;
            *(buffer+1) = 0xa3;
            return 2;
        case 0xb2: // Uppercase I, acute accent
            *buffer = 0xc3;
            *(buffer+1) = 0x8d;
            return 2;
        case 0xb3: // Uppercase I, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0x8c;
            return 2;
        case 0xb4: // Lowercase i, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0xac;
            return 2;
        case 0xb5: // Uppercase O, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0x92;
            return 2;
        case 0xb6: // Lowercase o, grave accent
            *buffer = 0xc3;
            *(buffer+1) = 0xb2;
            return 2;
        case 0xb7: // Uppercase O, tilde
            *buffer = 0xc3;
            *(buffer+1) = 0x95;
            return 2;
        case 0xb8: // Lowercase o, tilde
            *buffer = 0xc3;
            *(buffer+1) = 0xb5;
            return 2;
        case 0xb9: // Open curly brace
            *buffer = 0x7b;
            return 1;
        case 0xba: // Closing curly brace
            *buffer = 0x7d;
            return 1;
        case 0xbb: // Backslash
            *buffer = 0x5c;
            return 1;
        case 0xbc: // Caret
            *buffer = 0x5e;
            return 1;
        case 0xbd: // Underscore
            *buffer = 0x5f;
            return 1;
        case 0xbe: // Pipe (broken bar)
            *buffer = 0xc2;
            *(buffer+1) = 0xa6;
            return 1;
        case 0xbf: // Tilde
            *buffer = 0x7e; // Not sure
            return 1;
        case 0xc0: // Uppercase A, umlaut
            *buffer = 0xc3;
            *(buffer+1) = 0x84;
            return 2;
        case 0xc1: // Lowercase A, umlaut
            *buffer = 0xc3;
            *(buffer+1) = 0xa4;
            return 2;
        case 0xc2: // Uppercase O, umlaut
            *buffer = 0xc3;
            *(buffer+1) = 0x96;
            return 2;
        case 0xc3: // Lowercase o, umlaut
            *buffer = 0xc3;
            *(buffer+1) = 0xb6;
            return 2;
        case 0xc4: // Esszett (sharp S)
            *buffer = 0xc3;
            *(buffer+1) = 0x9f;
            return 2;
        case 0xc5: // Yen symbol
            *buffer = 0xc2;
            *(buffer+1) = 0xa5;
            return 2;
        case 0xc6: // Currency symbol
            *buffer = 0xc2;
            *(buffer+1) = 0xa4;
            return 2;
        case 0xc7: // Vertical bar
            *buffer = 0x7c;
            return 1;
        case 0xc8: // Uppercase A, ring
            *buffer = 0xc3;
            *(buffer+1) = 0x85;
            return 2;
        case 0xc9: // Lowercase A, ring
            *buffer = 0xc3;
            *(buffer+1) = 0xa5;
            return 2;
        case 0xca: // Uppercase O, slash
            *buffer = 0xc3;
            *(buffer+1) = 0x98;
            return 2;
        case 0xcb: // Lowercase o, slash
            *buffer = 0xc3;
            *(buffer+1) = 0xb8;
            return 2;
        case 0xcc: // Upper left corner
            *buffer = 0xe2;
            *(buffer+1) = 0x8c;
            *(buffer+2) = 0x9c;
            return 3;
        case 0xcd: // Upper right corner
            *buffer = 0xe2;
            *(buffer+1) = 0x8c;
            *(buffer+2) = 0x9d;
            return 3;
        case 0xce: // Lower left corner
            *buffer = 0xe2;
            *(buffer+1) = 0x8c;
            *(buffer+2) = 0x9e;
            return 3;
        case 0xcf: // Lower right corner
            *buffer = 0xe2;
            *(buffer+1) = 0x8c;
            *(buffer+2) = 0x9f;
            return 3;
        default: //
            *buffer = '?'; // I'll do it eventually, I promise
            return 1; // This are weird chars anyway
    }
}